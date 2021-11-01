/*
 * BangDBTSForecastHelper.h
 *
 *  Created on: May 15, 2021
 *      Author: sachin
 */

#ifndef SRC_BANGDBFORECASTTSDATA_H_
#define SRC_BANGDBFORECASTTSDATA_H_

#include "BangDBMLHelper.h"

/*
 * Timeseries data forecast works on taking the regular time stamped time series data and training a model for
 * future prediction.
 * It typically considers only following fields for training and predicting
 * 			timestamp (ts)
 * 			quantity (qty) - that we need to predict, it could be anything but has to be long or double
 * 			entityid (eid) - optional, but most of the time we wish to forecast for an entity
 * 	For training model using BangDBTSForecastHelper, we must provide info about these in the input file
 * 	Since input file could have more than these fields and it could be scattered, hence we must provide
 * 	the names of the these columns (CSV) and also the datatypes and positions at which they occur
 * 	For JSON file format, name is sufficient
 */

namespace BangDB_Client
{

class BangDBTSForecastHelper {
public:
	BangDBTSForecastHelper(BangDBMLHelper *bmlh);
	// the forecast method, takes in the input file and the type of the file
	// fileType = note that only "CSV", "JSON" is supported as of now
	int trainForecastModel(const char *inFile, const char *fileType);
	// the data could be a line or a file for forecast
	// fileType = "CSV", "JSON", "SVM"
	char *forecast(const char *data, const char *fileType, bool isFile);
	// provide the info about the fields for training
	//void setFieldInfo(BangDBTSFieldsInfo *finfo);
	void setFieldInfo(const char *fields[], int pos[], BANGDB_TS_DATA_TYPE dtypes[], int ndim);
	// path of local system where files will be stored, default is /tmp/
	void setBasePath(const char *basePath);
	// this is needed for training, even if we upload file
	void setSchemaName(const char *schemaName);
	// name of the model that will be created
	void setModelName(const char *modelName);
	// what should be the gran of data that should be computed for training?
	// default is day
	void setGran(BANGDB_TS_DATA_GRAN gran);
	// what should the aggregation menthod when data is rolled up
	// default is SUM
	void setAggrType(BANGDB_DATA_AGGR_TYPE aggr);
	// num of previous gran data to be selected, for ex; for day gran how many
	// previous days data should be considered
	void setLag(int lag);
	// what is the starting point? is it from today till lag or from few days offset till lag
	void setOffset(int offt);
	// if rollup is true then data would be rolled up for given gran
	void setShouldRollup(bool rollup);

	virtual ~BangDBTSForecastHelper();
private:
	bool _is_valid();

	BangDBMLHelper *_bmlh;
	//BangDBTSFieldsInfo *_finfo;
	const char *_fields[3];
	const char *_base_path;
	const char *_schema_name;
	const char *_model_name;
	BANGDB_TS_DATA_GRAN _gran;
	BANGDB_DATA_AGGR_TYPE _aggr;
	BANGDB_TS_DATA_TYPE _dtypes[3];
	int _pos[3];
	int _nfields;
	int _lag;
	int _offt;
	bool _rollup;
};
int summarize_data(const char *cfg, bool is_cfg_file, const char *ifile, const char *ofile, bool doprint);
}
#endif /* SRC_BANGDBFORECASTTSDATA_H_ */
