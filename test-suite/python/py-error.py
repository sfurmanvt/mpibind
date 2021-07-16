#!/usr/bin/env python3

import unittest
import syslog
import mpibind

xml_path = "../topo-xml/coral-lassen.xml"
mpibind.topology_set_xml(xml_path)

class TestError(unittest.TestCase):
    def setUp(self):
        self.handle = mpibind.MpibindHandle()

    def test_null_handle(self):
        with self.assertRaises(RuntimeError):
            self.handle.nthreads = -4
            self.handle.mpibind()
        

if __name__ == "__main__":
    from pycotap import TAPTestRunner
    suite = unittest.TestLoader().loadTestsFromTestCase(TestError)
    print(suite)
    TAPTestRunner().run(suite)