class CarimModelStaticMarkers extends CarimModelAbcMarkers {
    override void Persist() {
    }

    static CarimModelStaticMarkers GetFromConfig() {
        auto staticMarkerData = CfgGameplayHandler.GetCarimMapServerMarkers();
        auto result = new CarimModelStaticMarkers;

        foreach(auto data : staticMarkerData) {
            auto marker = CarimMapMarker.CarimNew(data.position, data.text, data.color, data.icon, CarimUtil.GetServerIdentifier());
            marker.CarimSetMarkerVisible3d(data.visible3d);
            marker.CarimSetMarkerHideGreaterThan(data.distanceHideGreaterThan);
            result.Add(marker);
        }

        return result;
    }
}
