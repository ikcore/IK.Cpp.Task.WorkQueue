# IK.Cpp.Task.WorkQueue
A simple work stealing queue system for cpp

Initialise the manager with any number of threads.
Inherit a work item into a custom class and override the execute method.
Add the work item to the manager queue.
The manager will then process the work item on the queue until all work complete.
