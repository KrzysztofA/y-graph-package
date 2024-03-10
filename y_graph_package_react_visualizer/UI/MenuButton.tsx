import React from "react";

import { View, Pressable, StyleSheet, Text, Animated } from "react-native";
import useMenuButtonHighlight from "./useMenuButtonHighlight";

const MenuButton = ({ title }: { title: string }): React.JSX.Element => {
  const [
    backgroundHighlightStyle,
    opacityHighlightStyle,
    activateHighlightSource,
    deactivateHighlightSource,
  ] = useMenuButtonHighlight();

  return (
    <Animated.View
      style={[
        styles.menuButton,
        opacityHighlightStyle,
        backgroundHighlightStyle,
      ]}>
      <Pressable
        onFocus={() => {
          activateHighlightSource(1);
        }}
        onBlur={() => {
          deactivateHighlightSource(1);
        }}
        onHoverIn={() => {
          activateHighlightSource(0);
        }}
        onHoverOut={() => {
          deactivateHighlightSource(0);
        }}>
        <View style={styles.menuButtonView}>
          <Text style={styles.menuButtonText}>{`${title}`}</Text>
        </View>
      </Pressable>
    </Animated.View>
  );
};

const styles = StyleSheet.create({
  menuButton: {
    padding: 5,
    paddingLeft: 18,
    paddingRight: 18,
  },
  menuButtonView: {
    borderBottomColor: "rgba(0, 0, 0, 0.4)",
    borderBottomWidth: 1,
  },
  menuButtonText: {
    color: "black",
    fontWeight: "700",
    paddingLeft: 3,
    paddingRight: 3,
    paddingTop: 6,
    paddingBottom: 6,
    fontSize: 16,
    textAlign: "center",
  },
});

export default MenuButton;
