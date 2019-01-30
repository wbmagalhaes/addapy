#include <Python.h>
#include "wrapper.h"

static char module_docstring[] = "A python wrapper for the Waveshare AD-DA board.";

// Functions
static PyObject *startADDA(PyObject *self, PyObject *args);
static PyObject *stopADDA(PyObject *self, PyObject *args);
static PyObject *readADC(PyObject *self, PyObject *args);
static PyObject *getChannelRaw(PyObject *self, PyObject *args);
static PyObject *getChannelVolts(PyObject *self, PyObject *args);
static PyObject *getAllChannelsRaw(PyObject *self, PyObject *args);
static PyObject *getAllChannelsVolts(PyObject *self, PyObject *args);
static PyObject *writeVoltsRef(PyObject *self, PyObject *args);
static PyObject *writeVolts(PyObject *self, PyObject *args);

static PyMethodDef module_methods[] = {
	{"start_adda", startADDA, METH_VARARGS, "Set gain, sampling rate, and scan mode."},
	{"stop_adda", stopADDA, METH_VARARGS, "End interface."},
	{"read_adc", readADC, METH_VARARGS, "Collect data from chip."},
	{"get_channel_raw", getChannelRaw, METH_VARARGS, "Read single channel."},
	{"get_channel_volts", getChannelVolts, METH_VARARGS, "Read single channel and convert to volts."},
	{"write_volts_ref", writeVoltsRef, METH_VARARGS, "Write single channel. ch_id, volt, vRef"},
	{"write_volts", writeVolts, METH_VARARGS, "Write single channel. ch_id, volt, vRef=5V"},
	{"get_all_channels_raw", getAllChannelsRaw, METH_VARARGS, "Read all channels."},
	{"get_all_channels_volts", getAllChannelsVolts, METH_VARARGS, "Read all channels and convert to volts."},
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
		return NULL;

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
		return NULL;

	adc = GetChannelRaw(ch_id);

	return Py_BuildValue("l", adc);
}

static PyObject *getChannelVolts(PyObject *self, PyObject *args)
{
	int ch_id;
	double volts;

	if (!PyArg_ParseTuple(args, "i", &ch_id))
		return NULL;

	volts = GetChannelVolts(ch_id);

	return Py_BuildValue("d", volts);
}

static PyObject *writeVoltsRef(PyObject *self, PyObject *args)
{
	int ch_id;
	float volts, vRef;

	if (!PyArg_ParseTuple(args, "iff", &ch_id, &volts, &vRef))
		return NULL;

	WriteVolts(ch_id, volts, vRef);

	return Py_BuildValue("");
}

static PyObject *writeVolts(PyObject *self, PyObject *args)
{
	int ch_id;
	float volts;

	if (!PyArg_ParseTuple(args, "if", &ch_id, &volts))
		return NULL;

	WriteVolts(ch_id, volts, 5);

	return Py_BuildValue("");
}

static PyObject *getAllChannelsRaw(PyObject *self, PyObject *args)
{	
	long int adc[8];
	GetAllChannelsRaw(adc);
	
	if (sizeof(adc) == 4)
		return Py_BuildValue("[l,l,l,l]", adc[0], adc[1], adc[2], adc[3]);
		
	return Py_BuildValue("[l,l,l,l,l,l,l,l]", adc[0], adc[1], adc[2], adc[3], adc[4], adc[5], adc[6], adc[7]);
}

static PyObject *getAllChannelsVolts(PyObject *self, PyObject *args)
{
	double volts[8];
	GetAllChannelsVolts(volts);

	if (sizeof(volts) == 4)
		return Py_BuildValue("[d,d,d,d]", volts[0], volts[1], volts[2], volts[3]);

	return Py_BuildValue("[d,d,d,d,d,d,d,d]", volts[0], volts[1], volts[2], volts[3], volts[4], volts[5], volts[6], volts[7]);
}