import React from "react";

import { StyleSheet, View } from "react-native";
import MenuButton from "../UI/MenuButton";

/**
 * Application Main Menu:
 * - Learn -> Goes to learn screen, where user can learn various algorithms
 * - Playground -> Allows user to create data structures and apply different algos
 * - Test -> Tests Algorithms showing their respective performance
 * - Author's Note/ Credits -> Self explanatory
 * - Exit -> Self explanatory
 * @returns
 */

const MainMenu = (): React.JSX.Element => {
  return (
    <View style={styles.mainMenuBox}>
      <MenuButton title={"Learn"} />
      <MenuButton title={"Playground"} />
      <MenuButton title={"Test"} />
      <MenuButton title={"Author's Note/ Credits"} />
      <MenuButton title={"Exit"} />
    </View>
  );
};

const styles = StyleSheet.create({
  mainMenuBox: {
    backgroundColor: "rgba(230, 220, 210, 0.5)",
    borderColor: "black",
    borderWidth: 2,
    borderRadius: 10,
    paddingTop: 20,
    paddingBottom: 20,
    maxWidth: 250,
    margin: 35,
    marginTop: 45,
    gap: 6,
  },
});

export default MainMenu;
