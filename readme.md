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
  <a href="https://github.com/othneildrew/Best-README-Template">
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

That's it ! So_long is now installed on your machine.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

To start the first map of the game, enter the following command in your terminal :
```
./so_long map/map1.ber
```

You can launch any map you want with the following syntax :
```
./so_long [map_name].ber
```

Keys :
* Deplacement : W,A,S,D or the arrow keys
* Exit the game : Escape
* Activate the fly cheat : V

<p align="right">(<a href="#readme-top">back to top</a>)</p>



## Map creation

To create a map, create a file with a .ber extension and fill it with the following characters :
- 0 : Air
- 1 : Walls, Floor and Ceiling
- P : Player starting position (Only 1)
- C : Collectibles (At least 1)
- E : Exit (At least 1)

The map needs to be a rectangle, else the game won't start.

For example the following file :

```
1111111
1P0C0E1
1111111
```
Gives the following map :

<img src="https://github.com/iel-amra/So_long/blob/main/img/screenshot_map.png?raw=true" alt="map-screenshot" width="500"/>

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Ihab El amrani - [Linkedin](www.linkedin.com/in/ihab-el-amrani) - iel-amra@student.42lyon.fr

Project Link: [https://github.com/iel-amra/So_long](https://github.com/iel-amra/So_long)

My github : [https://github.com/iel-amra](https://github.com/iel-amra)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: www.linkedin.com/in/ihab-el-amrani
[product-screenshot]: https://github.com/iel-amra/So_long/blob/main/img/screenshot.png?raw=true
[map-screenshot]: https://github.com/iel-amra/So_long/blob/main/img/screenshot_map.png?raw=true