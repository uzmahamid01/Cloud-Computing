Project 3 — Load balancer

[Detailed Design Overview](https://people.tamu.edu/~uzma_hamid/)

Overview

In this project, we will learn how to model a simulation of a large company's load-balancing web requests using a load balancer. We will simulate requests that contain Ip addresses from the requester, Ip addresses for the results, and a time (in clock cycles)

This project will require a real-world implementation of a queue. We also need a struct, a lower-level data structure that allows data to be contained in an object.

Load balancers are available commercially, but in this project, you will build one that has: ● Requests - generates random IP addresses, both in and out, and random times for each request to be processed. o IP in o IP out o Time (integer) ● Webserver(s) o Takes requests from the Load Balancer o Process the requests o Asks for another ● Load Balancer o Queue of requests o Keeps track of time.

Project Objectives:

You will be able to: ● Show your understanding of building and using a load balancer. ● Develop a guide for your load balancer that does not get overloaded or underutilized. Instructions:

This is an individual project. You must turn in your own work.
Collaboration for ideas between classmates is acceptable, but duplication of work is not.
Use C++ to write this program. A) you must design the workflow and write the driver or main program on your own. B) you must design the functions of the methods and classes you need, including the inputs and output of each function. C) you can then (and only after the design is complete) use ChatGPT to write the individual functions. For example, using ChatGPT, say "write a function in C++ that will take a real number value as US currency and convert it to Singapore currency". Your driver program or other functions can call that AI-written function.
Your program will contain multiple .cpp and .h files. The main program should set up the number of servers (user input), the time you want to run the load balancer (user input) and generate a full queue (usually servers * 100).
You will need a webserver class so you can create the number of webservers requested.
You will need a request class (or struct) that holds a request.
You will need a queue of type request. (called requestqueue?)
You will need a loadbalancer class that manages the webservers and the request queue. This should all for the creation of multiple load balancers and not just part of your driver program.
You will need to add new requests at random times to simulate new requests after the initial full queue you set up.
Dynamically allocate and deallocate web servers to mainian a balance with your requests.
Try different numbers as input to understand the capacity of your loadbalancer configurations.
All files must be commented with Doxygen using HTML output and loaded to a page on people.tamu.edu. Turn in this link. (having ChatGPT create Doxygen compensation is an excellent use of AI and acceptable in this assignment. Not many people like writing commentation of this type, but it is enjoyable seeing a tool create it for you.)
Demo the load balancer in your video.
Optional, add an IP range blocker to serve as a firewall or DOS attack prevention mechanism. If everything above works, and you choose this option, extra credit may be awarded.
Deliverables: All deliverables must be at least a minimum viable solution to the problem assigned. No attempt at grading will be made for non-substantial submissions. Create documentation for each of your code files in HTML, hosted on people.tamu.edu Create a log of 10 servers running for 10000 clock cycles Turn in your git repository link.
Demonstration of usability in your video. Create a make file and zip it together with all your .cpp and .h files. No executables. Turn in that zip file. This project is worth 100 points.

Documentation 30% Log and successful completion of load balancing 20% Demonstration, code, and Git usage 50%
