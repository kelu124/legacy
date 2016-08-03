import os,sys
from skimage import io
from skimage import restoration
import time
start_time = time.time()

kidney_image = io.imread("color_img.bmp")
#kidney_image = kidney_image[:,580:1096]
print kidney_image.shape

#estimate the noise in the image



#io.imshow (kidney_image) #have to set display to make this work


# do a test denosing using a total variation filter
kidney_image_denoised_tv = restoration.denoise_tv_chambolle(kidney_image, weight=0.05)
io.imsave('kidney_image_denoised_tv_test.bmp',kidney_image_denoised_tv)

# do a test denosing using a lateral filter to preserve edges
#kidney_image_denoised_lateral_test = restoration.denoise_bilateral(kidney_image, sigma_range=0.01, sigma_spatial=15, multichannel=False)

#io.imsave('kidney_image_denoised_lateral_test.bmp',kidney_image_denoised_lateral)

print("--- %s seconds ---" % (time.time() - start_time))
