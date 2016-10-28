# -*- coding: utf-8 -*-
from __future__ import unicode_literals
from django.core.files.storage import default_storage
from django.shortcuts import render

from django.core.paginator import Paginator, PageNotAnInteger, EmptyPage
from django.db.models.fields.files import FieldFile
from django.views.generic import FormView
from django.views.generic.base import TemplateView
from django.contrib import messages
from django.http import HttpResponseRedirect, HttpResponse
from .forms import FilesForm
import string,random, subprocess
from demo.models import Algorithm

import numpy
from skimage import io
from skimage import filter
from skimage import restoration
from skimage import measure
import time

def score(input, output):

    image_file_name1 = input
    image_file_name2 = output

    image_name1 = io.imread(image_file_name1)
    image_name2 = io.imread(image_file_name2)

    # estimate the standard deiviation of the images

    std_1 = numpy.std(numpy.std(numpy.array(image_name1)))
    std_2 = numpy.std(numpy.std(numpy.array(image_name2)))


    # print ("Standard deviation of the images are"%(std_1,std_2))

    # estimate the peak signal to noise ratio (PSNR) between the image

    peak_signal_to_noise_ratio = measure.compare_psnr(image_name1, image_name2)


    # estimate the mean square error between the images

    mse = measure.compare_mse(image_name1, image_name2)


    # estimate the normalised root mean square error between the images

    rmse = measure.compare_nrmse(image_name1, image_name2)


    score = rmse+mse+peak_signal_to_noise_ratio
    return {'rmse':rmse,'mse':mse,'peak_signal_to_noise_ratio': peak_signal_to_noise_ratio, 'score':score}




# http://yuji.wordpress.com/2013/01/30/django-form-field-in-initial-data-requires-a-fieldfile-instance/
class FakeField(object):
    storage = default_storage


fieldfile = FieldFile(None, FakeField, 'dummy.txt')


class HomePageView(TemplateView):
    template_name = 'demo/home.html'

    def get_context_data(self, **kwargs):
        context = super(HomePageView, self).get_context_data(**kwargs)
        messages.info(self.request, 'hello http://example.com')
        return context



class PaginationView(TemplateView):
    template_name = 'demo/pagination.html'

    def get_context_data(self, **kwargs):
        context = super(PaginationView, self).get_context_data(**kwargs)
        lines = []
        for i in range(200):
            lines.append('Line %s' % (i + 1))
        paginator = Paginator(lines, 10)
        page = self.request.GET.get('page')
        try:
            show_lines = paginator.page(page)
        except PageNotAnInteger:
            # If page is not an integer, deliver first page.
            show_lines = paginator.page(1)
        except EmptyPage:
            # If page is out of range (e.g. 9999), deliver last page of results.
            show_lines = paginator.page(paginator.num_pages)
        context['lines'] = show_lines
        return context


class MiscView(TemplateView):
    template_name = 'demo/misc.html'

class LeaderboardView(FormView):
    success_url = '/form_horizontal'
    template_name = 'demo/demo/form_with_files.html'
    form_class = FilesForm

    def get_context_data(self, **kwargs):

        context = super(LeaderboardView, self).get_context_data(**kwargs)
        context['layout'] = self.request.GET.get('layout', 'vertical')        
        context['object']= self.model
        return context

    def post(self, request, *args, **kwargs):
            form = self.form_class(request.POST, request.FILES)
            import uuid
            if form.is_valid():

                resp = self.handle_uploaded_file(request.FILES['file'])

                if resp['score'] < 100 :
                    button_type = 'btn-warning'
                else:
                    button_type = 'btn-success'
                self.uuid_index  = str(uuid.uuid4())
                id = self.uuid_index

                resp['score']= random.randint(1, 100)

                model = Algorithm

                run_rank = model.objects.filter(rating__gt=int(resp['score'])).order_by('ranking')
                if len(run_rank) > 0:
                    rankobj = run_rank.last()
                    rank = rankobj.ranking + 1

                else:
                    rank = 1

                run_rank_low = model.objects.filter(rating__lte=int(resp['score']))
                if len(run_rank_low) > 0 :
                    for i in run_rank_low:
                        print(i.ranking, i.rating)
                        i.ranking += 1
                        i.save()

                else:
                    pass


                b = Algorithm(run_id= id, name=''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(10)), ranking = rank, rating=resp['score'], button = button_type, time= resp['duration'], cpu=18)
                b.save()


                resp = model.objects.order_by('-rating')
                values = resp.values('run_id')
                for ind, item  in enumerate(values) :
                    if (item['run_id']) == self.uuid_index :
                        paging =  divmod(ind+1, 5)[0]
                
                return HttpResponseRedirect('/leaderboard?q=foo&flop=flip&page='+str(paging+1))

            else:
                render(request, self.template_name, {'form': form})


            return render(request, self.template_name, {'form': form})


    def get(self, request, *args, **kwargs):
            model = Algorithm
            resp = model.objects.order_by('-rating')
            paginator = Paginator(resp, 5)
            page = self.request.GET.get('page')
            try:
                resp = paginator.page(page)

            except PageNotAnInteger:
                # If page is not an integer, deliver first page.
                resp = paginator.page(1)
            except EmptyPage:
                # If page is out of range (e.g. 9999), deliver last page of results.
                resp = paginator.page(paginator.num_pages)

            return render(request, 'demo/form_with_files.html', {'form': self.form_class, 'button' :'btn-primary',  'object': resp})


    def handle_uploaded_file(self, f):
        from metrics import run_metrics
        with open('uploaded_custom.py', 'wb+') as destination:
            for chunk in f.chunks():
                destination.write(chunk)
            destination.close()

        ret = subprocess.check_output('python uploaded_custom.py', shell=True)
        import code_exec
        from code_exec import execute_user_script
        run_duration = execute_user_script()
        val_ret   = run_metrics('manu.jpg', 'denoise_image.jpg')
        val_ret['duration'] = run_duration
        return val_ret
