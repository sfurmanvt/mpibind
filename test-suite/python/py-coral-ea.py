#!/usr/bin/env python3

import unittest
import syslog
import mpibind





topology_file = "../topo-xml/coral-ea-hwloc1.xml"
answer_file = "./expected/expected.coral-ea"
mpibind.topology_set_xml(topology_file)

def parse_expected(answer_file):
    line_types = [
        'description',
        'thread_mapping',
        'cpu_mapping',
        'gpu_mapping'
    ]
    answers = []
    cur_answer = dict()
    type_idx = 0
    with open(answer_file, 'r') as f:
        for line in f.readlines():
            line = line.strip() 
            if line[0] == '#':
                continue
            if not line:
                continue

            cur_answer[line_types[type_idx]] = line
            type_idx += 1

            if type_idx = 4:
                answers.append(cur_answer)
                type_idx = 0
                cur_answer = dict()

    return answers


answers = parse_expected(answer_file)


class TestError(unittest.TestCase):
    def setUp(self):
        self.handle = mpibind.MpibindHandle()
        print(answers)
        
    def one_task_every_core(self):
        desc = 'Map one task to every core'


if __name__ == "__main__":
    from pycotap import TAPTestRunner
    suite = unittest.TestLoader().loadTestsFromTestCase(TestError)
    print(suite)
    TAPTestRunner().run(suite)