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

class MyMatchSpy extends XapianMatchSpy {
	var $calls=0;
	function __construct(){parent::__construct();}
	function apply($doc,$wt){
		assertEquals("XapianDocument", get_class($doc),"check matchspy arg is a doc");
		$this->calls++;
	}
}
class MyMatchDecider extends XapianMatchDecider {
	var $calls=0;
	function __construct(){parent::__construct();}
	function apply($doc){
		$this->calls++;
		assertEquals("XapianDocument", get_class($doc),"check mdecider arg is a doc");
		return true;
	}
}

for($pass=0;$pass<10;++$pass){
	//$db=Xapian::inmemory_open();
	$db=new XapianWritableDatabase("",Xapian::DB_BACKEND_INMEMORY);
	echo "pass:$pass\n";
	assertEquals("XapianWritableDatabase",get_class($db),"check inmemory_open returns a XapianWritableDatabase");
	assertEquals("WritableDatabase()", $db->get_description(),"check get_description return WritableDatabase()");
	assertEquals(0,$db->get_doccount(),"check doccount returns 0");
	$doc = new XapianDocument();
	assertEquals("XapianDocument",get_class($doc),"check doc is a XapianDocument");
	$doc->add_value(0,"value for slot 0");
	assertEquals("value for slot 0",$doc->get_value(0),"check document set/get_value");
	$doc->set_data("data");
	assertEquals("data",$doc->get_data(),"check document set_data/get_data");
	$tg=new XapianTermGenerator();
	$tg->set_stemmer(new XapianStem("fr"));

	$stopper = new XapianSimpleStopper();
	assertEquals("XapianSimpleStopper",get_class($stopper),"check stopper is a stopper");
	$stopper->add("et");

	$tg->set_stopper($stopper);
	assertEquals(true,$stopper->apply("et"),"check stopper detects stopwords");
	assertEquals(false,$stopper->apply("ett"),"check stopper detects only stopwords");

	$tg->set_database($db);
	$tg->set_document($doc);
	$tg->index_text("some text");
	$db->add_document($doc);
	assertEquals(1,$db->get_doccount(),"check doccount returns 1 after add_document");
	$queryParser = new XapianQueryParser();
	$query = $queryParser->parse_query("some text");
	assertEquals("XapianQuery", get_class($query),"check parse_query returns a query");
	assertEquals("Query((some@1 OR text@2))", $query->get_description(),"check query description");
	$enquire = new XapianEnquire($db);
	$enquire->set_query($query);
	assertEquals($query,$enquire->get_query(),"check enquire set/get query");
	$matchSpy=new MyMatchSpy;
	$enquire->add_matchspy($matchSpy);
	$mdecider = null;
	$mdecider = new MyMatchDecider();
	$mset = $enquire->get_mset(0,1,1,null,$mdecider);
	assertEquals("XapianMSet",get_class($mset),"check get_mset returns a MSet");
	assertEquals(1,$mset->size(),"check mset size");
	assertEquals(1,$matchSpy->calls,"check matchSpy called");
	$mdecider && assertEquals(1,$mdecider->calls,"check mdecider called");
	$mSetEnd = $mset->end();
	for($it=$mset->begin();!$it->equals($mSetEnd);$it->next()){
		$doc = $it->get_document();
		assertEquals("value for slot 0",$doc->get_value(0),"check found-document  value");
		$terms=[];
		$b=$doc->termlist_begin();
		$e=$doc->termlist_end();
		assertEquals("XapianTermIterator",get_class($b),"check term iterator type");
		assertEquals("XapianTermIterator",get_class($e),"check term iterator type");
		//echo("term:".$i->get_term())."\n";
		for($i=$b;!$i->equals($e);$i->next()) $terms[]=$i->get_term();
		assertEquals("Zsom, Ztext, some, text",join(", ",$terms),"check found-doc terms");
		$values=[];
		$b=$doc->values_begin();
		$e=$doc->values_end();
		for($i=$b;!$i->equals($e);$i->next()) $values[]=$i->get_valueno().":".$i->get_value();
		assertEquals("0:value for slot 0",join(", ",$values),"check found-doc values");
	}
	echo "ok\n";
	$db->close();
} 

