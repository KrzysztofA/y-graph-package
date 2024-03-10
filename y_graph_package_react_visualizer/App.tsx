import React from 'react';

import MainMenu from './Screens/MainMenu';
import {StyleSheet, View} from 'react-native';

function App(): React.JSX.Element {
  return (
    <View style={styles.mainView}>
      <MainMenu />
    </View>
  );
}

const styles = StyleSheet.create({
  mainView: {
    flex: 1,
    backgroundColor: 'white',
  },
});

export default App;
