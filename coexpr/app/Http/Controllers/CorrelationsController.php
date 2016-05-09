<?php

namespace App\Http\Controllers;

use App\Correlation;
use Request;
use Response;

class CorrelationsController extends Controller {

	public function index() {
		return "<a href=\"/correlations/bladder\">Bladder</a>";
	}

	public function bladder() {
		$correlations = Correlation::where('correlation', '>', 0.8)
			->where('correlation', '<', 1)
			->orderBy('correlation', 'desc')
			->paginate(25);

		if (Request::ajax())
			return Response::json(view('correlations._correlations')->with('correlations', $correlations)->render());

		return view('correlations.correlations')->with('correlations', $correlations);
	}

}
