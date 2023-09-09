#!/usr/bin/perl -w

use CGI;

$upload_dir = "../put_test";

$query = new CGI;

$filename = $query->param("photo");
$email_address = $query->param("email_address");
$filename =~ s/.*[\/\\](.*)/$1/;
$upload_filehandle = $query->upload("photo");

open UPLOADFILE, ">$upload_dir/$filename";

while ( <$upload_filehandle> )
{
  print UPLOADFILE;
}

close UPLOADFILE;

print $query->header ( );
print <<END_HTML;

<HTML>
<HEAD>
<TITLE>Thanks!</TITLE>
</HEAD>

<BODY>

<P>Thanks for uploading your photo!</P>
<P>Your email address: $email_address</P>
<P>Your photo:</P>
<img src="/put_test/$filename" border="0">

</BODY>
</HTML>

END_HTML
