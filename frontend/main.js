const currentPage = window.location.pathname.split('/').pop();

if(currentPage == "index.html")
{
    header  = document.querySelector('.header-container > header');
    header.innerHTML = "<p><a id=\"header-text\" href=\"editor.html\" title=\"Editor app\">Start Writing</a></p>";
}
else if(currentPage == "editor.html")
{
    header  = document.querySelector('.header-container > header');
   // header.innerHTML = "<p>Unimplemented</p>";
}
else 
{
    header  = document.querySelector('.header-container > header');
    header.innerHTML = "";
}