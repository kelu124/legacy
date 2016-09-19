__author__ = 'mehdibenchoufi'

from filereader import FileReader
from data import Data
from constants import Constants
import cv2
import cv

class ScanConverter:

    def get_input(self, value):
        return self.input

    def set_input(self, value):
        self.input = value

    def get_intermediate_input(self, value):
        return self.intermediate_input

    def set_intermediate_input(self, value):
        self.intermediate_input = value

    def get_output(self, value):
        return self.output

    def set_output(self, value):
        self.output = value

    def __init__(self, file_reader):
        #self.file_reader = FileReader()
        self.file_reader = file_reader
        self.data = Data()
        self.set_io(self.data)

    def set_io(self, data):
        self.set_input(data.get_src())
        self.set_intermediate_input(data.get_intermediate_src())
        self.set_output(data.get_destination())

    def converter(self, filereader):
        cv2.linearPolar(self.intermediate_input, (Constants.CENTER_POINT_x,Constants.CENTER_POINT_z), Constants.SCAN_CONVERTER_SCALE, cv2.INTER_CUBIC + cv2.WARP_INVERSE_MAP, self.output)
        cv2.imwrite('color_img.jpg', self.output)
        cv2.imshow('image',self.output)
        cv2.waitKey(0)


    def convert(self, filereader):
        rows = self.data.get_rows()
        cols = self.data.get_cols()
        for i in range(0,rows):
            for j in range(0,cols):
                self.input[i,j] = filereader.pixel_array[i*cols+j]
                self.intermediate_input[i,j] = filereader.pixel_array[i*cols+j]
        self.converter(filereader)
