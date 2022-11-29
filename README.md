# Project Status
I spent 2 days on this trying to get it working. I am working in areas that I have not worked in before so it was a really good learning experience for me. I learned things about ROS2 that I will be able to use in my own projects. 
The first problem I had is that the command to build the support for the new messages was missing from the examples I was working from and it took me .5 of a day to find the line to add to the CMakeList file. Once I found that the rest built fairly quickly. I had the ROS2 server code talking to the simulator Python code over sockets quickly. 
The next and biggest issue that I was unable to find the solution for is that the client is able to send a request and the server will ask the Python simulator for data and respond to the client with the data it received, but the client never gets the data. I am unsure if this is an issue with the client threading not processing the received data or some type of communication issue. 
With that issue unresolved I did not get on to running a second server. 
After trying so many different things from various examples I found the code is not as clean and commented as I would like. 
The system I am using for ROS2 development is a small PC with a Celeron processor so it was unable to run the client at 500Hz as the rest of the system would stop responding when I did. This may become an issue for the project I am wanting to use this machine for. That also may have been the cause of some of the problems I am having. My other ROS2 system is Raspberry Pi and I don't think it would have worked any better. 
I wish I had a working solution but it looks like I am missing something. All the code builds and runs but not with the expected results. I think if I was working as part of a team that someone looking over my code would be able to point out what the piece is that I am missing. 



# Robotic_HW
## Context
The design of our cells in Machina Labs has evolved over the past years. Currently, each of our cells has two articulated industrial robots on rails (a total of 7 axes) and a frame with hydraulic clamps. For the parts to form correctly, we must exert and maintain a dynamic force during the forming in a very accurate location in space. Currently, each robot is equipped with a load cell. See a quick video about our process [here](https://www.youtube.com/watch?v=iqYMprTEXRI). We are using ROS2 to collect the data from the network and control the robots in real-time. As a robotic engineer, we keep developing different modules for our network to add features to the system.  
 
## Objective
The goal of This project is to build a ROS2 network that collects data from 3-DOF sensors and makes the filtered data available as a ROS service and topic. Since we cannot send a real sensor to all of our applicants, we made a simple simulator (sensor.py) that mimics the behavior of a real sensor but with random data. 
- The first task is to make a costume service for 3-DOF sensor 
- The second task is to make a ROS2 service server that continuously reads data from the sensor and has the latest filter data available for the client service that you make. 
- Finally, please make a simple client that calls two of these services and publishes them a topic with 500Hz. Please keep in mind that your service servers can run slower than 500Hz. 
- You can define a second server in the simulator to modify the code and run two at the same time.
- You can check the example.py to see how to make calls to the sensor

## Grading Criteria
- We’re looking for code that is clean, readable, performant, and maintainable.
- The developer must think through the process of deploying and using the solution and provide the necessary documentation. 
- The sensor samples with 2000Hz, and you can request a specific number of samples in each call. Each call also has a ~1ms delay on top of the sampling time. We would like to hear your thought on picking the number of samples that you read in each call. 

## Submission
To submit the assignment, do the following:

1. Navigate to GitHub's project import page: [https://github.com/new/import](https://github.com/new/import)

2. In the box titled "Your old repository's clone URL", paste the homework repository's link: [https://github.com/Machina-Labs/robotic_hw](https://github.com/Machina-Labs/robotic_hw)

3. In the box titled "Repository Name", add a name for your local homework (ex. `Robotic_soln`)

4. Set the privacy level to "Public", then click "Begin Import" button at bottom of the page.

5. Develop your homework solution in the cloned repository and push it to GitHub when you're done. Extra points for good Git hygiene.

6. Send us the link to your repository.
