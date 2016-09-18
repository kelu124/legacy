import os,sys
from skimage import io
from skimage import filter

#kidney_image = io.imread("color_img.bmp")
#print kidney_image.shape

#estimate the noise in the image



#io.imshow (kidney_image) #have to set display to make this work


# do a test denosing using a total variation filter
#kidney_image_denoised_tv = filter.denoise_tv_chambolle(kidney_image, weight=0.1)
#io.imsave('kidney_image_denoised_tv.bmp',test_image_denoised_tv)

# do a test denosing using a lateral filter to preserve edges
#kidney_image_denoised_lateral = filter.denoise_bilateral(kidney_image, sigma_range=0.05, sigma_spatial=15)

# save the denoised image
#io.imsave('kidney_image_denoised_lateral.bmp',test_image_denoised_lateral)


