<?php

namespace App\Http\Controllers;

use App\Correlation;
use Request;
use Response;

class ExplorerController extends Controller {

	public function index() {
		return "<a href=\"/explorer/bladder\">Bladder</a><br><a href=\"/explorer/bladder\">Bladder</a>";
	}

	public function bladder($orderBy = 'desc', $from = 0.8, $to = 1) {
		$tissueName = 'Bladder';

		$correlations = Correlation::where('correlation', '>=', $from)
			->where('correlation', '<=', $to)
			->orderBy('correlation', $orderBy)
			->paginate(25);

		if (Request::ajax())
			return Response::json(view('explorer._explorer')->with('correlations', $correlations)->render());

		return view('explorer.explorer', compact('tissueName', 'correlations', 'orderBy', 'from', 'to'));
	}

}
