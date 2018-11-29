#include <Python.h>
#include "wrapper.h"

static char module_docstring[] = "A python wrapper for the Waveshare AD-DA board.";

// Functions
static PyObject *startADDA(PyObject *self, PyObject *args);
static PyObject *stopADDA(PyObject *self, PyObject *args);
static PyObject *readADC(PyObject *self, PyObject *args);
static PyObject *getChannelRaw(PyObject *self, PyObject *args);
static PyObject *getChannelVolts(PyObject *self, PyObject *args);
static PyObject *writeVolts(PyObject *self, PyObject *args);

static PyMethodDef module_methods[] = {
	{"start_adda", startADDA, METH_VARARGS, "Set gain, sampling rate, and scan mode."},
	{"stop_adda", stopADDA, METH_VARARGS, "End interface."},
	{"read_adc", readADC, METH_VARARGS, "Collect data from chip."},
	{"get_channel_raw", getChannelRaw, METH_VARARGS, "Read single channel."},
	{"get_channel_volts", getChannelVolts, METH_VARARGS, "Read single channel and convert to volts."},
	{"write_volts", writeVolts, METH_VARARGS, "Write single channel."},
	{NULL, NULL, 0, NULL}};

// Module specification
static struct PyModuleDef addapy_module = {
	PyModuleDef_HEAD_INIT,
	"addapy",		  /* name of module */
	module_docstring, /* module documentation, may be NULL */
	-1,				  /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
	module_methods};

PyMODINIT_FUNC PyInit_addapy(void)
{
	return PyModule_Create(&addapy_module);
}

static PyObject *startADDA(PyObject *self, PyObject *args)
{
	int gain, rate, mode;

	if (!PyArg_ParseTuple(args, "iii", &gain, &rate, &mode))
	{
		return NULL;
	}

	StartADDA(gain, rate, mode);
	return Py_BuildValue("");
}

static PyObject *stopADDA(PyObject *self, PyObject *args)
{
	StopADDA();
	return Py_BuildValue("");
}

static PyObject *readADC(PyObject *self, PyObject *args)
{
	ReadADC();
	return Py_BuildValue("");
}

static PyObject *getChannelRaw(PyObject *self, PyObject *args)
{
	int ch_id;
	long int adc;

	if (!PyArg_ParseTuple(args, "i", &ch_id))
	{
		return NULL;
	}

	adc = GetChannelRaw(ch_id);
	return Py_BuildValue("l", adc);
}

static PyObject *getChannelVolts(PyObject *self, PyObject *args)
{
	int ch_id;
	double volts;

	if (!PyArg_ParseTuple(args, "i", &ch_id))
	{
		return NULL;
	}

	volts = GetChannelVolts(ch_id);
	return Py_BuildValue("d", volts);
}

static PyObject *writeVolts(PyObject *self, PyObject *args)
{
	int ch_id;
	float volts, vRef;

	if (!PyArg_ParseTuple(args, "iff", &ch_id, &volts, &vRef))
	{
		return NULL;
	}

	WriteVolts(ch_id, volts, vRef);
	return Py_BuildValue("");
}