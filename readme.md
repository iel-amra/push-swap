<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/iel-amra/push_swap">
    <img src="https://github.com/iel-amra/push-swap/blob/master/Push_swap.png?raw=true" alt="Logo" width="400" height="400">
  </a>

  <h3 align="center">Push Swap - The sorting algorithm</h3>

  <p align="center">
    A special algorithm for a special case
  </p>
</div>



<!-- ABOUT THE PROJECT -->
## About The Project

Push Swap is a project at 42, a programming school, aimed at sorting algorithms. The goal of Push Swap is to write a program that sorts a stack of integers using a limited set of operations. The main challenge is to find the most efficient sorting algorithm and minimize the number of operations performed.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Rules

* The game is composed of two stacks named a and b.
* To start, a contains a random number of either positive or negative integers without any duplicates, with b empty.
* The goal is to sort the numbers in stack a in ascending order.

## Operations Allowed
* sa: swap the first two elements of stack a
* sb: swap the first two elements of stack b
* ss: sa and sb simultaneously
* pa: push the first element of stack a onto stack b
* pb: push the first element of stack b onto stack a
* ra: rotate stack a (shift all elements up by one). The first element becomes the last.
* rb: rotate stack b (shift all elements up by one). The first element becomes the last.
* rr: ra and rb simultaneously.
* rra: reverse rotate stack a (shift all elements down by one). The last element becomes the first.
* rrb: reverse rotate stack b (shift all elements down by one). The last element becomes the first.
* rrr: rra and rrb simultaneously.

## The Algorithm
The algorithm used utilize a custom variant of radix in base 4 (2 bits) that I optimezed to minimze the number of operations. Since a simple application of this radix transfer the numbers from one stack to the other, it needs 2 operations to get the numbers in stack a again, wich is equivalent to sorting 4 bits of the numbers. The maximum bits are sorted with this algorithm, and if there are 3 or less unsorted bits, they are sorted with another completely custom algorithm wich is implemented in the line_algo.c file.

<!-- GETTING STARTED -->
## Getting Started

Push Swap was developed and tested only on ubuntu, but should work well on other debian based distribution

### Installation

1. Clone the repo
   ```sh
   git clone git@github.com:iel-amra/push-swap.git
   ```
2. Enter the push_swap folder and compile
   ```
   cd push_swap && make
   ```

That's it ! push_swap is now installed on your machine.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

```
./push_swap [list of integers]
```

## Example

```
$> ./push_swap 4 67 3 87 23
sa
rra
pb
pb
sa
pa
pa
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## Author
This project was developed by Ihab El Amrani for 42.

<!-- CONTACT -->
## Contact

Ihab El amrani - [Linkedin](https://www.linkedin.com/in/ihab-el-amrani) - iel-amra@student.42lyon.fr

Project Link: [https://github.com/iel-amra/So_long](https://github.com/iel-amra/So_long)

My github : [https://github.com/iel-amra](https://github.com/iel-amra)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/ihab-el-amrani
[product-screenshot]: https://github.com/iel-amra/push_swap/blob/main/img/screenshot.png?raw=true