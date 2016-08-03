efrom filereader import FileReader
from scanconverter import ScanConverter

__author__ = 'mehdibenchoufi'

def run():
    file_reader = FileReader("data_kydney")
    scanconversion = ScanConverter(file_reader)
    scanconversion.convert(file_reader)

run()
