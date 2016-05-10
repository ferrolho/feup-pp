<?php

namespace App\Http\Controllers;

use App\Correlation;
use Request;
use Response;

class CorrelationsController extends Controller {

	public function index() {
		return "<a href=\"/correlations/bladder\">Bladder</a>";
	}

	public function bladder($orderBy = 'desc', $from = 0.8, $to = 1) {
		$correlations = Correlation::where('correlation', '>=', $from)
			->where('correlation', '<=', $to)
			->orderBy('correlation', $orderBy)
			->paginate(25);

		if (Request::ajax())
			return Response::json(view('correlations._correlations')->with('correlations', $correlations)->render());

		return view('correlations.correlations', compact('correlations', 'orderBy', 'from', 'to'));
	}

}
