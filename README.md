# portfolio
#### Video Demo:
https://youtu.be/gR-z828yz3o?si=kC-frEDTS9kEe8wO

## What my project is and why I made it:
This is a portfolio website for me to use someday. (This is my first foray into computer science, so there are no actual projects or CV content yet!)

## Project file contents and function:
- The static folder contains pictures used in the website (favicon, background and project pictures) and the styles.css file, which contains styling for the entire website.
- The templates file contains all the html pages, including layout.html (boilerplate code) and all the pages that use it (cv, projects, and the homepage "index").
- Outside these folders is app.py, which contains routes to the homepage, cv page, and projects page. app.py renders each template at their respective route.
- The "requirements.txt" file lists the libraries used to make the website. The website was made using HTML, CSS, Flask, and Bootstrap.

## Resources used:
- [W3 Schools CSS tutorial](https://www.w3schools.com/css/default.asp) for CSS help
- [Bootstrap Tutorials](https://www.youtube.com/playlist?list=PLH3tw9J9QyRrur30b9eDOtxh6yf4MqN5T) to get started with Bootstrap
- [Bootstrap Docs](https://getbootstrap.com/docs/5.3/getting-started/introduction/) for further Bootstrap help
- My DNA picture was made by ANIRUDH on [unsplash](https://unsplash.com/photos/a-close-up-of-a-double-strand-of-gold-glitter-YQYacLW8o2U)

## Reasoning for current design choices:
I wanted to have separate CV, projects, and home pages because as I accumulate work experience and make personal projects, I don't want my portfolio to become cluttered. I chose a grid layout for the projects page as opposed to a list because it's more space efficient and, in my opinion, more visually interesting to look at.


## Future features:
In future versions of this site, I want to add a "back-to-top" button and proper hamburger menu for the CV and projects pages. Specifically, I want to make a hamburger menu similar to the one in [this video](https://www.youtube.com/watch?v=OFKBep95lb4) where he animated the menu so it transitions from a hamburger to an "X" when you click it and the menu slides out. Rather than having it cover the whole screen as in his version, I want it to slide out and push the rest of the page content a bit to the side.

I also want to add a contact link, such that when you hover over it or click it, it opens up a drawer of social media icons that hyperlink to my profiles. I want the drawer to open horizontally on the homepage and vertically in the hamburger menu.

Eventually I may want to add a back-end with a database with two tables:
- a projects table where each row is 1 project, which gets its own page. 1 cell in a row is a project picture and the other cell contains details of the project.
- a CV table where each row is 1 section in the cv html template. 1 cell in a row is the date and the other cell contains details about the role/experience.

I also want to change the CV positioning for smaller screens (768px and below), so it looks more aesthetically pleasing.
