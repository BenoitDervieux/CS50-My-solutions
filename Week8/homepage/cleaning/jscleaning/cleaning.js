
function toggle() {
    var x = document.getElementById("calendarToBook");
    if (x.style.opacity === "1" ) {
        x.style.opacity = "0";
        x.style.transition = "opacity 300ms ease-in-out";
        x.style.visibility = "hidden";
        x.style.transition = "visibility 300ms ease-in-out";
        

    } else {
        
        x.style.visibility = "visible";
        x.style.transition = "visibility 300ms ease-in-out";
        x.style.opacity = "1";
        x.style.transition = "opacity 300ms ease-in-out";
        
    }
}