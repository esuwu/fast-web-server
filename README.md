# C++ fast-web-server based on thread pool

## How to install:
- mkdir build && cd build
- cmake ..
- make
- ./fast-web-server # works on 8081 port

## Functional testing:
test_directory_index (__main__.HttpServer)
directory index file exists ... ok
test_document_root_escaping (__main__.HttpServer)
document root escaping forbidden ... ok
test_empty_request (__main__.HttpServer)
Send empty line ... ok
test_file_in_nested_folders (__main__.HttpServer)
file located in nested folders ... ok
test_file_not_found (__main__.HttpServer)
absent file returns 404 ... ok
test_file_type_css (__main__.HttpServer)
Content-Type for .css ... ok
test_file_type_gif (__main__.HttpServer)
Content-Type for .gif ... ok
test_file_type_html (__main__.HttpServer)
Content-Type for .html ... ok
test_file_type_jpeg (__main__.HttpServer)
Content-Type for .jpeg ... ok
test_file_type_jpg (__main__.HttpServer)
Content-Type for .jpg ... ok
test_file_type_js (__main__.HttpServer)
Content-Type for .js ... ok
test_file_type_png (__main__.HttpServer)
Content-Type for .png ... ok
test_file_type_swf (__main__.HttpServer)
Content-Type for .swf ... ok
test_file_urlencoded (__main__.HttpServer)
urlencoded filename ... ok
test_file_with_dot_in_name (__main__.HttpServer)
file with two dots in name ... ok
test_file_with_query_string (__main__.HttpServer)
query string with get params ... ok
test_file_with_slash_after_filename (__main__.HttpServer)
slash after filename ... ok
test_file_with_spaces (__main__.HttpServer)
filename with spaces ... ok
test_head_method (__main__.HttpServer)
head method support ... ok
test_index_not_found (__main__.HttpServer)
directory index file absent ... ok
test_large_file (__main__.HttpServer)
large file downloaded correctly ... ok
test_post_method (__main__.HttpServer)
post method forbidden ... ok
test_request_without_two_newlines (__main__.HttpServer)
Send GET without to newlines ... ok
test_server_header (__main__.HttpServer)
Server header exists ... ok

----------------------------------------------------------------------
Ran 24 tests in 0.024s

OK

## Loading tesing fast-web-server:
This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking 127.0.0.1 (be patient)
Completed 5000 requests
Completed 10000 requests
Completed 15000 requests
Completed 20000 requests
Completed 25000 requests
Completed 30000 requests
Completed 35000 requests
Completed 40000 requests
Completed 45000 requests
Completed 50000 requests
Finished 50000 requests


Server Software:        fast-http-server
Server Hostname:        127.0.0.1
Server Port:            8081

Document Path:          /httptest/text..txt
Document Length:        5 bytes

Concurrency Level:      1000
Time taken for tests:   2.915 seconds
Complete requests:      50000
Failed requests:        0
Total transferred:      7100000 bytes
HTML transferred:       250000 bytes
Requests per second:    17154.81 [#/sec] (mean)
Time per request:       58.293 [ms] (mean)
Time per request:       0.058 [ms] (mean, across all concurrent requests)
Transfer rate:          2378.89 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    2  43.7      0    1031
Processing:     0    1  12.0      0     864
Waiting:        0    0  12.0      0     864
Total:          0    3  50.5      0    1889

Percentage of the requests served within a certain time (ms)
  50%      0
  66%      0
  75%      0
  80%      0
  90%      0
  95%      1

## Loading tesing nginx:
This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient)
Completed 5000 requests
Completed 10000 requests
Completed 15000 requests
Completed 20000 requests
Completed 25000 requests
Completed 30000 requests
Completed 35000 requests
Completed 40000 requests
Completed 45000 requests
Completed 50000 requests
Finished 50000 requests


Server Software:        nginx/1.18.0
Server Hostname:        localhost
Server Port:            80

Document Path:          /httptest/text..txt
Document Length:        5 bytes

Concurrency Level:      1000
Time taken for tests:   1.304 seconds
Complete requests:      50000
Failed requests:        99631
   (Connect: 0, Receive: 0, Length: 50117, Exceptions: 49514)
Total transferred:      118584 bytes
HTML transferred:       2430 bytes
Requests per second:    38336.00 [#/sec] (mean)
Time per request:       26.085 [ms] (mean)
Time per request:       0.026 [ms] (mean, across all concurrent requests)
Transfer rate:          88.79 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0   13   3.2     13      23
Processing:     2   13   3.3     13      33
Waiting:        0    0   1.5      0      24
Total:         22   26   1.8     25      47

Percentage of the requests served within a certain time (ms)
  50%     25
  66%     26
  75%     26
  80%     26
  90%     28
  95%     29
  98%     32
  99%     32
 100%     47 (longest request)
