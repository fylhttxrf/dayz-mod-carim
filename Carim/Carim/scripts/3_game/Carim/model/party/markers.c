class CarimModelPartyMarkers extends CarimModelAbcMarkers {}

class CarimModelPartyPings extends CarimModelAbcMarkers {
    override void Add(MapMarker mark) {
        int maxPings = CfgGameplayHandler.GetCarimPartyMaxPings();
        if (maxPings > 0 && markers.Count() >= maxPings) {
            markers.RemoveOrdered(0);
        }
        super.Add(mark);
    }
}

class CarimModelPartyPositiosn extends CarimModelAbcMarkers {}
