function toggle() {
    var x = document.getElementById("prep");
    var y = document.getElementById("clickHere");
    var z = document.getElementById("clickHere2");


    if (x.style.display === "none" ) {
        x.style.display = "block";
        y.style.display = "none";
        z.style.display = "block";
    } else {
        x.style.display = "none"
        y.style.display = "block";
        z.style.display = "none";
    }
}