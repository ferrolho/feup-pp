<?php

namespace App\Http\Controllers;

use App\Correlation;
use Illuminate\Http\Request;

use App\Http\Requests;

class HomeController extends Controller {

	/**
	 * Create a new controller instance.
	 *
	 * @return void
	 */
	public function __construct() {
		//$this->middleware('auth');
	}

	/**
	 * Show the application dashboard.
	 *
	 * @return \Illuminate\Http\Response
	 */
	public function index() {
		$correlations = Correlation::all();

		return view('correlations')->with('correlations', $correlations);
	}

}
