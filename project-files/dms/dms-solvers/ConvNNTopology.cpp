#include "ConvNNTopology.h"

using namespace dms::solvers::neural_nets::conv_net;

ConvNNTopology::ConvNNTopology(int input_weight, int input_heigth, int input_depth, List<ILayer^>^ layers)
{
	w = input_weight;
	h = input_heigth;
	d = input_depth;

	if (layers->Count == 0)
		throw gcnew System::ArgumentException("� ���� ��� �����");

	this->layers = gcnew List<ILayer^>();
	layerDimentions = gcnew List<VolumeDimention^>();

	int bw = w;
	int bh = h;
	int bd = d;
	for (int i = 0; i < layers->Count; i++)
	{
		this->layers->Add(layers[i]);
		auto d = gcnew VolumeDimention();
		if (layers[i]->GetType() == FullyConnectedLayer::typeid)
		{
			auto l = (FullyConnectedLayer^)layers[i];
			bw = d->Width = 1;	
			bh = d->Heigth = 1;	
			bd = d->Depth = l->NeuronsCount;
		}
		else if (layers[i]->GetType() == ConvolutionLayer::typeid)
		{
			auto l = (ConvolutionLayer^)layers[i];
			bw = d->Width = calcOutputVolume(bw, l->FilterWidth, l->Padding, l->StrideWidth);	
			bh = d->Heigth = calcOutputVolume(bh, l->FilterHeight, l->Padding, l->StrideHeight);
			bd = d->Depth = l->CountFilters;
		}
		else if (layers[i]->GetType() == PoolingLayer::typeid)
		{
			auto l = (PoolingLayer^)layers[i];
			bw = d->Width = calcOutputVolume(bw, l->FilterWidth, 0, l->StrideWidth);
			bh = d->Heigth = calcOutputVolume(bh, l->FilterHeight, 0, l->StrideHeight);
			d->Depth = bd;
		}
		layerDimentions->Add(d);
	}
}

int ConvNNTopology::calcOutputVolume(int input, int filter, int padding, int stride)
{
	int temp = input - filter + 2 * padding;
	if ((temp < 0) || ((temp % stride) != 0))
	{
		throw gcnew System::ArgumentOutOfRangeException("������ �����������");
	}
	return temp / stride + 1;
}

int ConvNNTopology::GetInputWidth() { return w; }
int ConvNNTopology::GetInputHeigth() { return h; }
int ConvNNTopology::GetInputDepth() { return d; }
int ConvNNTopology::GetInputsCount() { return w*h*d; }
int ConvNNTopology::GetOutputsCount()
{
	VolumeDimention^ l = layerDimentions[layerDimentions->Count - 1];
	return l->Width * l->Heigth * l->Depth;
}
List<ILayer^>^ ConvNNTopology::GetLayers() { return layers; }

List<ConvNNTopology::VolumeDimention^>^ ConvNNTopology::GetVolumeDimentions() { return layerDimentions; }