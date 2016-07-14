<?php
$db=Xapian::inmemory_open();echo get_class($db).chr(10);echo $db->get_description().chr(10);$db->close();
