Team members: Caitlyn & Lily
Last modified: 22/07/2025

<h2>1. Which data structure performs faster on the inventory lookups and why?</h2>
   The binary tree performs faster for this because it does not have to look through every element of its structure; it can look through subtrees that avoid data (the left/right subtree from the root) it does not have to search through.
<h2>2. Report execution times for each data structure required on tests 1, 6, 7, 8, 9.</h2>
<ul>
   <li><b>Test 1:</b> 
      <ul>
         <li>Singly linked list-2.7428e-05 seconds</li>
         <li>Doubly linked list-0.00954073 seconds (linked list test)</li>
         <li>Doubly linked list-0.000346429 seconds (binary tree test)</li>
         <li>Binary tree-2.167e-06 seconds</li>
      </ul>
   </li>
   <li><b>Test 6:</b> 
      <ul>
         <li>Singly linked list-5.112e-06 seconds</li>
         <li>Doubly linked list-0.327238 seconds (linked list test)</li>
         <li>Doubly linked list-0.00282209 seconds (binary tree test)</li>
         <li>binary tree-3.271e-06 seconds</li>
      </ul>
   </li>
   <li><b>Test 7:</b> 
      <ul>
         <li>Singly linked list-4.4e-06 seconds</li>
         <li>Doubly linked list-1.6241 seconds (linked list test)</li>
         <li>Doubly linked list-0.0202627 seconds (binary tree test) </li>
         <li>Binary tree-2.398e-06 seconds</li>
      </ul>
   </li>
   <li><b>Test 8:</b> 
      <ul>
         <li>Singly linked list-7.635e-06 seconds</li>
         <li>Doubly linked list-11.5402 seconds (linked list)</li>
         <li>Doubly linked list-0.393936 seconds (binary tree test)</li>
         <li>Binary tree-2.125e-06 seconds</li>
      </ul>
   </li>
   <li><b>Test 9:</b> 
      <ul>
         <li>Singly linked list-3.3634e-05 seconds</li>
         <li>Doubly linked list-175.382 seconds (linked list test)</li>
         <li>Doubly linked list-52.1866 seconds (binary tree test)</li>
         <li>Binary tree-1.8256e-05 seconds</li>
      </ul>
   </li>
</ul>
<h2>3. What might be a consequence of making the inventory sorted? If you made the inventory sorted, did you notice any differences?</h2>
    Making the inventory sorted will increase the time it takes to perform inventory lookups. Since the inventory elements need to look through the data structure to find the spot where it should go, additional time is required to complete this additonal action. This would add a worst-case scenario big O(n).
<h2>4. What Linux command(s) might one use to monitor the performance of a running process, especially to check if its performance is bound by either CPU or I/O?</h2>
    The Linux 'time' command is specifically used to determine how long a command takes to run and can be used in this case to test the performance of a running process. A tool that can give the real-time process statistics, including CPU and I/O time is 'htop' command, but looking at the CPU and I/O specifically also has their own tools. The command 'iotop' is a tool that monitors the disk I/O usage in real time by processes, and can be used to test the performance of a running process by viewing its activity in I/O. To view activity in CPU, the 'top' or 'vmstat' commands which will allow viewing of the CPU statistics or the virtual memory statistics, respectively.



<h2>Other tests and known issues/important notes</h2>
<li>If two movies have the exact same name, the one which is found first in the inventory will be used.</li>
<li>Tested inventory construction and handling of doubles by running ./blockbuster with the count_test.tsv and double_test.tsv files respectively.</li>
<li>The binary tree defaults to adding nodes to the left, unless the value being inserted is less than the current node.</li>
