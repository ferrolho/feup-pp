<?php

namespace App\Http\Controllers;

use App\Correlation;
use Illuminate\Http\Request;

use App\Http\Requests;

class CorrelationsController extends Controller {

	public function index() {
		return "<a href=\"/correlations/bladder\">Bladder</a>";
	}

	public function bladder() {
		$correlations = Correlation::where('correlation', '>', 0.8)
			->where('correlation', '<', 1)
			->orderBy('correlation', 'desc')
			->paginate(25);

		//$correlations = Correlation::paginate(100);

		return view('correlations')->with('correlations', $correlations);
	}

}
