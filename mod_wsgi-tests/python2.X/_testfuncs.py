import os
import httplib
import re
import time

host = 'wsgi-tests.example.com'
port = '11111'

host = os.environ.get('WSGI_TESTS_HOST', host)
port = int(os.environ.get('WSGI_TESTS_PORT', port))

log_file = '/var/log/apache2/%s-error_log' % host
log_delay = '0.1'

log_file = os.environ.get('WSGI_TEST_LOG_FILE', log_file)
log_delay = float(os.environ.get('WSGI_TEST_LOG_DELAY', log_delay))

def connection():
    connection = httplib.HTTPConnection(host, port)
    connection.connect()
    return connection

class Log(object):

    def __init__(self, filename):
        self.__filename = filename
        self.__fp = open(self.__filename, 'r')
        self.__fp.seek(0, os.SEEK_END)
        self.__errors = None

    def output(self, index):
        if not self.__errors is None:
            return self.__errors[index]
        time.sleep(1)
        self.__errors = []
        for line in self.__fp.readlines():
            match = re.match(r'(\[[^]]*\]) (\[[^]]*\]) ([^]]*\]) (.*)', line)
            if match:
                groups = match.groups()
                line = groups[1] + ' ' + groups[3]
            else:
                match = re.match(r'(\[[^]]*\]) (.*)', line)
                if match:
                    groups = match.groups()
                    line = groups[1]
            self.__errors.append(line)
        return self.__errors[index]

def messages():
    return Log(log_file)
