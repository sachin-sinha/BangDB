/*
 * BangDBDataParser.h
 *
 *  Created on: May 15, 2021
 *      Author: sachin
 */

#ifndef SRC_BANGDBDATAPARSER_H_
#define SRC_BANGDBDATAPARSER_H_

#include "BangDBCommon.h"

namespace BangDB_Client
{
class BangDBDataParser {
public:
	BangDBDataParser();
	void reset();
	int init(const char *parse_cfg_file, bool isfile = true);
	int parse_file(const char *ifile_path, const char *ofile_path);
	//int parse_stream(const char *schema_name, const char *stream_name, int duration_sec, int lag_sec, const char *ofile_path);
	int parse_line(const char *iline, int niline, char **oline);
	long get_num_lines_parsed();
	void print_stats();
	double get_attr_val(const char *attr, int op);
	void print_stats_pretty();
	virtual ~BangDBDataParser();

private:
	long ptbparse;
};
}
#endif /* SRC_BANGDBDATAPARSER_H_ */
