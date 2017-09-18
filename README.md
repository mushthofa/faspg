FASPG
==========================================

Fuzzy Answer Set Programming (FASP) approach to Gene Regulatory Networks (GRN) dynamics and attractor computations.

The system provides a way to compute the dynamics of Gene Regulatory Networks (GRN) and find their attractors.
A (partial) description of the system is available on:

- Mushthofa, Mushthofa, Steven Schockaert, and Martine De Cock. "Computing attractors of multi-valued gene regulatory networks using fuzzy answer set programming." Fuzzy Systems (FUZZ-IEEE), 2016 IEEE International Conference on. IEEE, 2016.

As a requirement, you need to install first FFASP: our FASP solver implementation, available at:

https://github.com/mushthofa/ffasp
 
After installing FFASP, FASPG can be compiled and executed with:

-- "./faspg  < network | ffaspg " for computing steady state attractors
-- "./faspga < network c | ffaspg " for finding cyclic attractors of sizes up to c


Examples networks for the benchmark used in our latest paper: Modeling Multi-Valued Biological Interaction Networks using Fuzzy Answer Set Programming (under revision)
can be found in the subfolders: newinst/ and revinst/. 




