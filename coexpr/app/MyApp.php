<?php namespace App;

class MyApp extends \Illuminate\Foundation\Application {

	public function publicPath() {
		return $this->basePath . DIRECTORY_SEPARATOR . '..' . DIRECTORY_SEPARATOR . 'html';
	}

}
