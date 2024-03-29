<?php

use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateCorrelationsTables extends Migration {

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

	/**
	 * Run the migrations.
	 *
	 * @return void
	 */
	public function up() {
		foreach ($this->tissues as $tissue) {
			Schema::connection(str_slug($tissue))->create('correlations', function (Blueprint $table) {
				$table->increments('id');

				$table->string('gene1');
				$table->string('gene2');
				$table->float('correlation');
			});
		}
	}

	/**
	 * Reverse the migrations.
	 *
	 * @return void
	 */
	public function down() {
		foreach ($this->tissues as $tissue) {
			Schema::connection(str_slug($tissue))->drop('correlations');
		}
	}

}
