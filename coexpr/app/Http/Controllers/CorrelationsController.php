<?php

namespace App\Http\Controllers;

use App\Correlation;
use Illuminate\Http\Request;

use App\Http\Requests;

class CorrelationsController extends Controller {

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
		return "<a href=\"/correlations/bladder\">Bladder</a>";
	}

	public function bladder() {
		$correlations = Correlation::where('correlation', '>', 0.9)
			->where('correlation', '<', 1)
			->orderBy('correlation', 'desc')
			->paginate(100);

		//$correlations = Correlation::paginate(100);

		return view('correlations')->with('correlations', $correlations);
	}

}
