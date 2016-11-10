def install_packages():
    import pip
    pip.main(['install', 'aesop'])

def run(file):
    import io
    import os
    import sys
    import argparse
    from skimage import io
    from skimage import filter
    from skimage import restoration
    from skimage import measure
    kidney_image = io.imread(file)
    # estimate the noise in the image
    # do a test denosing using a total variation filter
    kidney_image_denoised_tv = restoration.denoise_tv_chambolle( kidney_image, weight=0.1)
    dir  = os.path.split(file)[0]
    filename = os.path.split(file)[1]    
    io.imsave(dir+'/denoise_'+filename, kidney_image_denoised_tv)
