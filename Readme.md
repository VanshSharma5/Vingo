## Requirements 
1. gcc 
    To compile the Bussiness logic written in C.

2. a2emon or mod_ssl 
    a2enmod (Apache 2 enable module) is a management script used in specific Linux distributions (e.g., Debian, Ubuntu) to simplify the process of enabling available Apache modules. 

3. apache2/httpd
    Apache HTTPD (or apache2 on Debian/Ubuntu) is a free, open-source, and highly popular web server software that acts as a bridge, listening for client requests (like a browser asking for a webpage) and delivering website content (HTML, images, etc.)

4. Text Editor for magic
    Now Don't said you can do all without it.

## Setup Apache 
1. Edit "/etc/apache2/sites-available/example.com.conf"(For Debian)
   Edit "/etc/httpd/sites-available/example.com.conf"(For REHL)
   Edit find Yourserf (For Windows)

    """
    ScriptAlias /cgi-bin "/usr/lib/cgi-bin/example.com" 
    <Directory "/usr/lib/cgi-bin/example.com/">
        Options +ExecCGI 
    </Directory>
    """
    NOTE: This "/usr/lib/cgi-bin/example.com" is a path where the server find the files to render. You must not worry.
    If any difference in defined or actual path you must encounter internal server error 500

2. Reload Apache
    sudo service apache2 reload
    sudo systemctl restart httpd

# Use Vingo
1. compile the code 
    $ gcc myfile.c -o /usr/lib/cgi-bin/example.com/myfile

2. launch your browser to the url
    http://localhost/cgi-bin/example.com/myfile

    NOTE: The myfile in path is same as file name.


## Warning
1. Specify "Content-Type: text/html" as
    printf("Content-Type: text/html \n\n");

2. It is must to add two new line character after "Content-Type: text/html \n\n"

3. Don't use <!DOTYPE HTML>
    I also don't Know

