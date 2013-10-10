<?php
header("Content-type: text/xml");
echo chr(60).chr(63).'xml version="1.0" encoding="utf-8" '.chr(63).chr(62);
?>
<Customers>
  <Customer>
    <Firstname>Manuel</Firstname>
    <Lastname>Silva</Lastname>
    <email>silva@bloggs.com</email>
  </Customer>
  <Customer>
    <Firstname>Carlos</Firstname>
    <Lastname>Lopes</Lastname>
    <email>carlos@ygmail.com</email>
  </Customer>
  <Customer>
    <Firstname>Marvin</Firstname>
    <Lastname>Martian</Lastname>
    <email>marvin@mars.com</email>
  </Customer>
</Customers>

