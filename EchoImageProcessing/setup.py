__author__ = 'mehdibenchoufi'
from setuptools import setup, find_packages
setup(
    name='ImageProcessing',
    version='0.1',
    description='image_processing',
    classifiers=[
        "Programming Language :: Python",
    ],
    packages=find_packages(),
    install_requires=[
        'scikit-image',
        'numpy',
        'cv2'
    ],
)




