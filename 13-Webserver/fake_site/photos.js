let container = document.getElementById("photo_container");
let responseText;


function	findFiles()
{
	let xmlHttp = new XMLHttpRequest();
	xmlHttp.open("GET", "/uploads/", false);
	xmlHttp.send(null);
	responseText = xmlHttp.responseText;
}

findFiles();

if (responseText.includes("<title>Index of /uploads/</title>"))
{
	if (responseText.match(/a href="([a-z]|\.|[0-9])*/g) === null)
	{
		container.innerHTML = "<p>There are no photos in gallery! Be the first to upload something</p>";
	}
	else
	{
		let photos = responseText.match(/a href="([a-z]|\.|[0-9])*/g);
		let numPhoto = photos.length;
		for (let i = 0; i < numPhoto; i++)
		{
			if (photos[i] != "a href=\"..")
			{
				let node = document.createElement("img");
				node.src = "uploads/" + photos[i].substr(8);
				node.style.width = "32vw";
				container.appendChild(node);
			}
		}
	}
}
else
{
	container.innerHTML = "<p>Autoindex is off, so I, the Javascript code, can't get the already uploaded photos :(</p><br><p><a href=\"uploads\">Click me</a> to find out!</p>";
}
