import { useEffect, useState, useMemo } from "react";
import useMultiSourceCondition from "../Hooks/useMultiSourceCondition";
import { Animated } from "react-native";

const useMenuButtonHighlight = () => {
const [animation, setAnimation] = useState(new Animated.Value(0));

  const backgroundHighlightStyle = {
    backgroundColor: animation.interpolate({
      inputRange: [0, 1],
      outputRange: ["rgba(255, 255, 255, 0)", "rgba(210, 210, 210, 1)"],
    }),
  };
  const opacityHighlightStyle = {
    opacity: animation.interpolate({
      inputRange: [0, 1],
      outputRange: ["0.8", "1"],
    }),
  };
  const [highlight, activateHighlightSource, deactivateHighlightSource] = useMultiSourceCondition(2);
  const highlightAnimation = useMemo(
    () =>
      Animated.timing(animation, {
        toValue: 1,
        duration: 200,
        useNativeDriver: false,
      }),
    [animation],
  );
  const unhighlightAnimation = useMemo(
    () =>
      Animated.timing(animation, {
        toValue: 0,
        duration: 200,
        useNativeDriver: false,
      }),
    [animation],
  );

  useEffect(() => {
    if (highlight) {
      unhighlightAnimation.stop();
      highlightAnimation.start();
    } else {
      highlightAnimation.stop();
      unhighlightAnimation.start();
    }
  }, [highlight, highlightAnimation, unhighlightAnimation]);

  return [backgroundHighlightStyle, opacityHighlightStyle, activateHighlightSource, deactivateHighlightSource] as const;
}

export default useMenuButtonHighlight;