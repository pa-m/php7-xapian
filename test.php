<?php

function assertEquals($e,$a,$msg){
	$ok = gettype($a)==gettype($e);
	if($ok && is_object($e)){
		$ok=get_class($a)==get_class($e);
	}
	if($ok && is_array($e)){
		$ok=count($a)==count($e);
		if($ok){
			foreach ($e as $key => $value) {
				if($a[$key]!=$e[$key]) {$ok=false;break;}
			}
		}
	}
	if($ok) $ok=$a==$e;
	echo ($ok ? "ok   ":"FAILED")."\t$msg\n";
	if(!$ok) echo "actual:".var_export($a,1)."\n";
}

$db=Xapian::inmemory_open();
assertEquals("XapianWritableDatabase",get_class($db),"check inmemory_open returns a XapianWritableDatabase");
assertEquals("WritableDatabase()", $db->get_description(),"check get_description return WritableDatabase()");
assertEquals(0,$db->get_doccount(),"check doccount returns 0");
$doc = new XapianDocument();
assertEquals("XapianDocument",get_class($doc),"check doc is a XapianDocument");
$doc->set_data("data");
assertEquals("data",$doc->get_data(),"check document set_data/get_data");
$tg=new XapianTermGenerator();
//$tg->set_stemmer(new XapianStem("fr"));
$stopper = new XapianSimpleStopper();
assertEquals("XapianSimpleStopper",get_class($stopper),"check stopper is a stopper");
$stopper->add("et");

$tg->set_stopper($stopper);
assertEquals(true,$stopper->apply("et"),"check stopper detects stopwords");
assertEquals(false,$stopper->apply("ett"),"check stopper detects only stopwords");
$tg->set_database($db);
echo "before set doc\n";
$tg->set_document($doc);
echo "before index text\n";
$tg->index_text("some text");
echo "before add doc\n";
$db->add_document($doc);
assertEquals(1,$db->get_doccount(),"check doccount returns 1 after add_document");

$db->close();
echo "ok";
