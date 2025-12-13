# 😍 Vingo 🕸️Web 🌐Devlopment In C 😘

## Requirements 
1. **gcc** 
    <p> To compile the Bussiness logic written in C. </p>

2. **a2emon or mod_ssl (optional)**
    <p>a2enmod (Apache 2 enable module) is a management script used in specific Linux distributions (e.g., Debian, Ubuntu) to simplify the process of enabling available Apache modules. </p>

3. **apache2/httpd**
    <p>Apache HTTPD (or apache2 on Debian/Ubuntu) is a free, open-source, and highly popular web server software that acts as a bridge, listening for client requests (like a browser asking for a webpage) and delivering website content (HTML, images, etc.)</p>
    Dounload Links and ways

    * **Debian** : `sudo dnf install httpd`
    * **REHL** : `sudo apt-get install apache`
    * **Windows** : Download the binaries from [Apache Lounge](https://www.apachelounge.com/download/) and extract To your C: Drive

4. **Git Bash**
    <p>It is being use to automate the entire process <strong>parsing -> compiling -> transfering</strong> </p>

5. **Text Editor**
    <p>Now Don't said you can do all without it.</p>

## Config Apache (Optional)
1. Edit "/etc/httpd/conf/httpd.conf" (For Debian)
2. Edit "/etc/httpd/conf/httpd.conf" (For REHL)
3. Edit "C:/Apache2.4/conf/httpd.conf " (For Windows)

    >[!TIP] Modifu this only if you want custamize path else leave it unchange.
    <pre>ScriptAlias /cgi-bin "/usr/lib/cgi-bin/example.com"
        &ltDirectory "/usr/lib/cgi-bin/example.com/"&gt
            Options +ExecCGI 
        &lt/Directory&gt</pre>

    >[!NOTE]: This "/usr/lib/cgi-bin/example.com" is a path where the server find the files to render. You must not worry.<br>
    > If any difference in defined or actual path you must encounter code 
    <br>**404** if path is correct but file not found
    <br>**500** if path is incorrect or file contain any error

## Start Apache Serving us
1. For Debian based systems `sudo service apache2 reload`
2. For REHL based systems `sudo systemctl restart httpd`
3. For Windows 
    1. `httpd.exe -k start` To run in Background
    2. `httpd.exe` To run for Current terminal Session
    >[!NOTE]: You could find in bin directory of Apache24 folder<br>
    > if the background start not work try forground start (do not close the terminal window because if close apache/httpd stop serving)

# Use Vingo
## Automatic

1. **compile the code**
    ```bash
    $ git clone https://github.com/VanshSharma5/Vingo.git
    $ cd Vingo
    $ sh ./htmltobin.sh
    ```


2. **launch your browser to the url(for defaults apache config)**
    ```bash
    $ firefox http://localhost/cgi-bin/example.com/myfile
    ```
    >[!NOTE]: The myfile in path is same as file name and by changing the filename in the url can access all your files you parsed and compiled successfully.

## Manual
**It suported But not documented Yet. It is easier to understand. Please figure Yourself**

## Warning
1. Do Not use `<!DOTYPE HTML>` in the html file.

2. Instead of `<!DOTYPE HTML>` you have to specify 
    ```python
    Content-Type: text/html 


    ```
    >[!ERROR] It is must to add two lines after `Content-Type: text/html ` , because if not then it will raise an internal server error 500.
