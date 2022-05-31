# C++ fast-web-server based on thread pool

## How to install:
- mkdir build && cd build
- cmake ..
- make
- ./fast-web-server # works on 8081 port

## config:
- httpd.conf

## Load tesing fast-web-server:
```
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
```
## Loading tesing nginx:
```
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
```
