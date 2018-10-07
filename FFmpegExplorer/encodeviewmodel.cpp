#include "encodeviewmodel.hpp"

EncodeViewModel::EncodeViewModel(QObject *parent) : ViewModelBase(parent)
{
    set_encodeItems(new QQmlObjectListModel<EncodeItemViewModel>(this));

    auto encodeItems = get_encodeItems();

    auto eivm = new EncodeItemViewModel(this);
    eivm->set_inputFileName("ddd");
    eivm->set_outputFileName("aaazaazzaaz");

    encodeItems->append(eivm);

    eivm = new EncodeItemViewModel(this);
    eivm->set_inputFileName("ghg");
    eivm->set_outputFileName("aaazaazzaaz");
    encodeItems->append(eivm);

    eivm = new EncodeItemViewModel(this);
    eivm->set_inputFileName("wowza");
    eivm->set_outputFileName("aaazaazzaaz");
    encodeItems->append(eivm);

    eivm = new EncodeItemViewModel(this);
    eivm->set_inputFileName("wowza2");
    eivm->set_outputFileName("aaazaazzjaaz");
    encodeItems->append(eivm);

}

void EncodeViewModel::startEncode()
{
    get_encodeItems();

    auto eivm = new EncodeItemViewModel(this);
        eivm->set_inputFileName("wowza");
        eivm->set_outputFileName("aaazaazzaaz");

    get_encodeItems()->append(eivm);
    get_encodeItems()->at(0)->set_inputFileName("WOW!");

    //findChild
    //encodeItemsChanged(get_encodeItems());
}
