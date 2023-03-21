# Berkley-Algorithm
Each computer in the network periodically sends its local time to a designated "master" computer, which then computes the correct time for the network based on the received timestamps.
 -An individual node is chosen as the master node from a pool node in the network. This node is the main node in the network which acts as a master and the rest of the nodes act as slaves. The master node is chosen using an election process/leader election algorithm.
 
 
- Master node periodically pings slaves nodes and fetches clock time at them using Cristian’s algorithm.


-Master node calculates the average time difference between all the clock times received and the clock time given by the master’s system clock itself. This average time difference is added to the current time at the master’s system clock and broadcasted over the network.
