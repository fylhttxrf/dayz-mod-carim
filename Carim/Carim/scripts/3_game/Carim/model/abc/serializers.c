#ifndef CARIM_CarimModelAbcSerializers
#define CARIM_CarimModelAbcSerializers

class CarimModelAbcSerializers extends Managed {
    // A fairly hacky way to get around lack of support for templated
    // classes with inheritance

    static bool LoadFile(Class target, out string error) {
        switch (target.ClassName()) {
            case "CarimModelSettings":
                auto data0 = CarimModelSettings.Cast(target);
                return JsonFileLoader<CarimModelSettings>.LoadFile(data0.Path(), data0, error);
                break;
            case "CarimModelChatSettings":
                auto data1 = CarimModelChatSettings.Cast(target);
                return JsonFileLoader<CarimModelChatSettings>.LoadFile(data1.Path(), data1, error);
                break;
            case "CarimModelMapMarkers":
                auto data2 = CarimModelMapMarkers.Cast(target);
                return JsonFileLoader<CarimModelMapMarkers>.LoadFile(data2.Path(), data2, error);
                break;
            case "CarimModelPartyMarkers":
                auto data3 = CarimModelPartyMarkers.Cast(target);
                return JsonFileLoader<CarimModelPartyMarkers>.LoadFile(data3.Path(), data3, error);
                break;
            case "CarimModelPartyRegistrations":
                auto data4 = CarimModelPartyRegistrations.Cast(target);
                return JsonFileLoader<CarimModelPartyRegistrations>.LoadFile(data4.Path(), data4, error);
                break;
        }
        error = "Unknown serializer type";
        return false;
    }

    static bool SaveFile(Class target, out string error) {
        switch (target.ClassName()) {
            case "CarimModelSettings":
                auto data0 = CarimModelSettings.Cast(target);
                return JsonFileLoader<CarimModelSettings>.SaveFile(data0.Path(), data0, error);
                break;
            case "CarimModelChatSettings":
                auto data1 = CarimModelChatSettings.Cast(target);
                return JsonFileLoader<CarimModelChatSettings>.SaveFile(data1.Path(), data1, error);
                break;
            case "CarimModelMapMarkers":
                auto data2 = CarimModelMapMarkers.Cast(target);
                return JsonFileLoader<CarimModelMapMarkers>.SaveFile(data2.Path(), data2, error);
                break;
            case "CarimModelPartyMarkers":
                auto data3 = CarimModelPartyMarkers.Cast(target);
                return JsonFileLoader<CarimModelPartyMarkers>.SaveFile(data3.Path(), data3, error);
                break;
            case "CarimModelPartyRegistrations":
                auto data4 = CarimModelPartyRegistrations.Cast(target);
                return JsonFileLoader<CarimModelPartyRegistrations>.SaveFile(data4.Path(), data4, error);
                break;
        }
        error = "Unknown serializer type";
        return false;
    }
}

#endif
