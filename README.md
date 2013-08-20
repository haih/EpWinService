EpWinService
=======================
#### Windows Service Management Solution for Custom Windows Program ####


DESCRIPTION
-----------

EpWinService is a Visual C++ framework that supports making multiple custom applications as Windows Services under a [MIT License](http://opensource.org/licenses/mit-license.php).
It enables to manage each custom application services through Administration Server 
EpWinService supports Visual C++ 2005/2008/2010/2012.
Source can be downloaded at [EpWinService](http://github.com/juhgiyo/epwinservice)


FEATURES
--------

* Easy to make custom applications as service by setting up properties file.
* Able to register/manage multiple custom applications as services.
* Supports Stop/Start/Restart operation on custom application service
* Supports Pre/Post-Process Command before/after application run
* Supports fault-tolerance (automatic-restart) for application's abnormal termination
* Supports Custom-Process Command to be run through Administration Server
* Supports all operation on application service through Administration Server
* Supports the properties change of application service through Administration Server
* Supports API Library (EpWinServiceAPILibrary) for the client-side application development
* Supports Auto-Deploy System based on SVN


DOCUMENTATION
-------------

For detailed documentation, please download the full document 
- [EpWinService Documentation.chm](https://s3.amazonaws.com/elasticbeanstalk-us-east-1-052504677345/Downloads/EpWinService/EpWinService+Documentation.chm)
- [EpWinServiceAPILibrary Documentation.chm](https://s3.amazonaws.com/elasticbeanstalk-us-east-1-052504677345/Downloads/EpWinService/EpWinServiceAPILibrary+Documentation.chm)

If the documentation file is not visible after finishing download,
* Solution 1.
  1. Double-click the .chm file.
  2. In the Open File-Security Warning dialog box, click to clear the Always ask before opening this file check box.
  3. Click Open.
* Solution 2.
  1. Right-click the CHM file, and then click Properties.
  2. Click Unblock.
  3. Double-click the .chm file to open the file.


USAGE
-----

To find the usage examples, please see the [wiki page](https://github.com/juhgiyo/EpWinService/wiki)


REFERENCE
---------
* [EpServerEngine](https://github.com/juhgiyo/EpServerEngine)
* [EpLibrary 2.0](https://github.com/juhgiyo/EpLibrary)


LICENSE
-------

[The MIT License](http://opensource.org/licenses/mit-license.php)

Copyright (c) 2013 Woong Gyu La <[juhgiyo@gmail.com](mailto:juhgiyo@gmail.com)>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
