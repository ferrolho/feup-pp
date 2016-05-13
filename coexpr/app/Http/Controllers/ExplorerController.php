<?php

namespace App\Http\Controllers;

use DB;
use Request;
use Response;

class ExplorerController extends Controller {

	private $tissues = [
		"Adipose - Subcutaneous",
		"Adipose - Visceral (Omentum)",
		"Adrenal Gland",
		"Artery - Aorta",
		"Artery - Coronary",
		"Artery - Tibial",
		"Bladder",
		"Brain - Amygdala",
		"Brain - Anterior cingulate cortex (BA24)",
		"Brain - Caudate (basal ganglia)",
		"Brain - Cerebellar Hemisphere",
		"Brain - Cerebellum",
		"Brain - Cortex",
		"Brain - Frontal Cortex (BA9)",
		"Brain - Hippocampus",
		"Brain - Hypothalamus",
		"Brain - Nucleus accumbens (basal ganglia)",
		"Brain - Putamen (basal ganglia)",
		"Brain - Spinal cord (cervical c-1)",
		"Brain - Substantia nigra",
		"Breast - Mammary Tissue",
		"Cells - EBV-transformed lymphocytes",
		"Cells - Transformed fibroblasts",
		"Colon - Sigmoid",
		"Colon - Transverse",
		"Esophagus - Gastroesophageal Junction",
		"Esophagus - Mucosa",
		"Esophagus - Muscularis",
		"Heart - Atrial Appendage",
		"Heart - Left Ventricle",
		"Kidney - Cortex",
		"Liver",
		"Lung",
		"Minor Salivary Gland",
		"Muscle - Skeletal",
		"Nerve - Tibial",
		"Ovary",
		"Pancreas",
		"Pituitary",
		"Prostate",
		"Skin - Not Sun Exposed (Suprapubic)",
		"Skin - Sun Exposed (Lower leg)",
		"Small Intestine - Terminal Ileum",
		"Spleen",
		"Stomach",
		"Testis",
		"Thyroid",
		"Uterus",
		"Vagina",
		"Whole Blood"
	];

	public function index() {
		return view('explorer.index')->with('tissues', $this->tissues);
	}

	public function explore($tissueName, $orderBy = 'desc', $from = 0.8, $to = 1) {
		$correlations = DB::connection($tissueName)
			->table('correlations')
			->where('correlation', '>=', $from)
			->where('correlation', '<=', $to)
			->orderBy('correlation', $orderBy)
			->paginate(25);

		$tissueName = ucfirst($tissueName);

		if (Request::ajax())
			return Response::json(view('explorer._explorer')->with('correlations', $correlations)->render());

		return view('explorer.explorer', compact('tissueName', 'correlations', 'orderBy', 'from', 'to'));
	}

}
