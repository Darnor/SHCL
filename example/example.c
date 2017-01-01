/*
 * Copyright (C) 2016 Hansruedi Patzen
 *
 * This file is part of SHCL.
 *
 * SHCL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SHCL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SHCL. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Sample implementation for a program using the SHCL Library
 */

#include <shcl.h>

#include <stdio.h>

int main() {
	// Specify image dimensions.
	int columns = 2048;
	int rows = 1024;

	// Specify the number of images to transform. (Must be >= 1)
	int numberOfImages = 1;

	// Specify the maximum l you want to calculate.
	// This must be smaller than the number of rows!
	int maxL = 10;

	// Create an error object to allow passing erros from the library to the application.
	shcl_error error = NULL;
	
	// Create an info object with all information needed for the transform.
	shcl_info_const info = shcl_create_info(
				SHCL_MENDEZ,
				SHCL_ROW_MAJOR,
				columns,
				rows,
				numberOfImages,
				maxL,
				SHCL_CPU,
				SHCL_HOLLINGSWORTH,
				SHCL_SCALE_SYMMETRIC,
				&error
			);

	// Check if an error happend and if so print it to std::cout, destroy the current state including the error!
	if (error) {
		// Print the error message.
		printf ("Error while creating info: %s", shcl_error_message(error));
		shcl_destroy_error(error);
		shcl_destroy_info(info);
		return 1;
	}

	// Allocate space for the input data. 
	// It will be enough for the specified image dimensions and numbers.
	shcl_complex * inData = shcl_calloc_image(info, &error);
	
	// As alwys check for an error and do the cleanup if true.
	if (error) {
		printf ("Error while allocating input data memory info: %s", shcl_error_message(error));
		shcl_destroy_error(error);
		shcl_free(inData);
		shcl_destroy_info(info);
		return 1;
	}

	// Allocate space for the output data.
	// It will be enough for all clm depending on the transform type.
	shcl_complex * outData = shcl_calloc_clm(info, &error);

	// Error check and cleanup if true.
	if (error) {
		printf ("Error while allocating output data memory info: %s", shcl_error_message(error));
		shcl_destroy_error(error);
		shcl_free(inData);
		shcl_free(outData);
		shcl_destroy_info(info);
		return 1;
	}

	// Fill input data.
	for (int t = 0; t < numberOfImages; ++t) {
		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < columns; ++c) {

				// Get the image array index.
				int index = shcl_image_index(info, c, r, t, &error);

				// Error check and cleanup if true.
				if (error) {
					printf ("Error while calculating image index: %s", shcl_error_message(error));
					shcl_destroy_error(error);
					shcl_free(inData);
					shcl_free(outData);
					shcl_destroy_info(info);
					return 1;
				}

				// Fill image data point.
				inData[index][0] = (double)(c);
				inData[index][1] = 0;
			}
		}
	}

	// Create a plan with the given info, data and direction.
	shcl_plan plan = shcl_create_plan(info, inData, outData, SHCL_FORWARD, &error);

	// Error check and cleanup if true.
	if (error) {
		printf ("Error while creating the shcl plan: %s", shcl_error_message(error));
		shcl_destroy_error(error);
		shcl_free(inData);
		shcl_free(outData);
		shcl_destroy_plan(plan);
		shcl_destroy_info(info);
		return 1;
	}

	// Execute the transformation by executing the plan.
	shcl_execute_plan(plan, &error);

	// Error check and cleanup if true.
	if (error) {
		printf ("Error while executing the shcl plan: %s", shcl_error_message(error));
		shcl_destroy_error(error);
		shcl_free(inData);
		shcl_free(outData);
		shcl_destroy_plan(plan);
		shcl_destroy_info(info);
		return 1;
	}

	// Print the transformed coefficients.
	for (int i = 0; i < numberOfImages; ++i) {
		printf ("Image no. %d\n", (i + 1));
		for (int l = 0; l <= maxL; ++l) {

			// Get the image index. If since this is the Méndez-Transform the m is always equal 0.
			int index = shcl_coefficient_index(info, l, 0, i, &error);

			// Error check and cleanup if true.
			if (error) {
				printf ("Error while calculating the clm index: %s", shcl_error_message(error));
				shcl_destroy_error(error);
				shcl_free(inData);
				shcl_free(outData);
				shcl_destroy_plan(plan);
				shcl_destroy_info(info);
				return 1;
			}
			printf ("(%f, %f)\n", outData[index][0], outData[index][1]);
		}
	}

	// Do a final cleanup after finishing all the work.
	// This includes destroying the error!
	shcl_destroy_error(error);
	shcl_free(inData);
	shcl_free(outData);
	shcl_destroy_plan(plan);
	shcl_destroy_info(info);
	return 0;
}

