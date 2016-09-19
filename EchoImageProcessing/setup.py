__author__ = 'mehdibenchoufi'
from setuptools import setup, find_packages
setup(
    name='EchoImageProcessing',
    version='0.1',
    description='echography image processing',
    classifiers=[
        "Programming Language :: Python",
    ],
    packages=find_packages(),
    install_requires=[
        'scikit-image',
        'numpy',
    ],
    entry_points={
        'console_scripts': [
            'image_metrics=EchoImageProcessing.image_metrics:main',
            'scanconverter=EchoImageProcessing.scanconverter:main',
            'denoise_image=EchoImageProcessing.denoise_image:main', 
        ],
    },

)




