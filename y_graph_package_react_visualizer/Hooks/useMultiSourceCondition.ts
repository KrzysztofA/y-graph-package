import { useEffect, useState } from "react";

const useMultiSourceCondition = ( sources : number ) => {
  const [conditionSource, setConditionSource] = useState(() => { 
    let temp : Array<number> = Array(sources);
    temp.fill(0);
    return temp;
  });
  const [condition, setCondition] = useState(false);

  useEffect(() => {
    if(conditionSource.includes(1)) setCondition(true);
    else setCondition(false);
  }, [conditionSource]);

  const activateSource = ( sourceIndex : number ) => {
    setConditionSource(() => conditionSource.map((el, index) => index == sourceIndex ? 1 : el));
  };

  const deactivateSource = ( sourceIndex : number ) => {
    setConditionSource(() => conditionSource.map((el, index) => index == sourceIndex ? 0 : el));
  };

  return [ condition, activateSource, deactivateSource ] as const;
}

export default useMultiSourceCondition;