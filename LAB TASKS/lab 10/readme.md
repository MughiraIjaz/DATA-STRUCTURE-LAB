Student Performance Analytics System

Overview
This program analyzes student academic records using a singly linked list and dynamic memory allocation. All input is taken from a text file and all results are written to output files.

Features Implemented
- Dynamic linked list storage
- Multiple sorting operations using different algorithms
- File-based input and output
- Data validation and anomaly reporting
- Duplicate student ID detection
- Student search by ID
- Sorting performance statistics

Sorting Algorithms Used
1. Bubble Sort
   Used for:
   - Ranking by CGPA
   - Department-wise sorting
   - Alphabetical sorting of names
   Reason: Simple to implement for linked lists and works well with partially sorted data.

2. Selection Sort
   Used for:
   - Sorting by enrollment year and student ID
   Reason: Straightforward comparison-based algorithm suitable for linked lists.

Files Generated
- ranked_by_cgpa.txt
- sorted_by_enrollment.txt
- department_analysis.txt
- performance_tiers.txt
- data_issues.txt
- duplicates_report.txt
- search_results.txt
- algorithm_performance.txt

How to Compile
g++ student_performance.cpp -o student_performance

How to Run
./student_performance

Assumptions
- Student names may contain spaces
- Input file format is correct
- Credit hours increase reasonably with semester

Complexity Analysis
Bubble Sort: O(n^2)
Selection Sort: O(n^2)
Space Complexity: O(n)

Author
BS Artificial Intelligence / Computer Science Student

